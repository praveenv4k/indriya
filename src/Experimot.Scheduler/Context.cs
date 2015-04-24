using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Collections.Specialized;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using Caliburn.Micro;
using experimot.msgs;
using Experimot.Scheduler.Annotations;
using Experimot.Scheduler.Data;
using Experimot.Scheduler.Tasks;
using Nancy.TinyIoc;
using Quartz;
using Quartz.Impl;
using Xceed.Wpf.Toolkit.PropertyGrid.Attributes;
using Xceed.Wpf.Toolkit.PropertyGrid.Editors;
using ILog = Common.Logging.ILog;
using LogManager = Common.Logging.LogManager;

namespace Experimot.Scheduler
{
    public class Context : INotifyPropertyChanged
    {
        private Robot _robot;
        private readonly BindableCollection<Human> _humans;
        private readonly IDictionary<string, ManipulatableObject> _objects;
        private readonly object _object = new object();
        private readonly BindableCollection<GestureModule> _motionModules;
        private readonly BindableCollection<RobotBehaviorModule> _behaviorModules;
        private static readonly ILog Log = LogManager.GetLogger<Context>();
        private readonly BrowserTabViewModel _browserTabViewModel;

        public Context()
        {
            //_humans = new ConcurrentDictionary<int, Human>();
            _humans = new BindableCollection<Human>();
            _robot = new Robot();
            _objects = new ConcurrentDictionary<string, ManipulatableObject>();
            _motionModules = new BindableCollection<GestureModule>();
            _behaviorModules = new BindableCollection<RobotBehaviorModule>();
            _browserTabViewModel = new BrowserTabViewModel("http://localhost:8888");
        }

        [ExpandableObject]
        public Robot Robot
        {
            get { return _robot; }
            private set
            {
                if (Equals(value, _robot)) return;
                _robot = value;
                OnPropertyChanged();
            }
        }

        //[ExpandableObject]
        [Editor(typeof (CollectionEditor), typeof (CollectionEditor))]
        public BindableCollection<Human> Humans
        {
            get { return _humans; }
        }

        [ExpandableObject]
        public IDictionary<string, ManipulatableObject> Objects
        {
            get { return _objects; }
        }

        [ExpandableObject]
        public BindableCollection<GestureModule> MotionModules
        {
            get { return _motionModules; }
        }

        [ExpandableObject]
        public BindableCollection<RobotBehaviorModule> BehaviorModules
        {
            get { return _behaviorModules; }
        }

        public BrowserTabViewModel TabViewModel
        {
            get { return _browserTabViewModel; }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null) handler(this, new PropertyChangedEventArgs(propertyName));
        }

        public void Update(Pose pose)
        {
            lock (_object)
            {
                Robot.Localization.SetPose(pose);
            }
        }

        public void Update(SensorData sensorData)
        {
            lock (_object)
            {
                Robot.SensorData = sensorData;
            }
        }

        public void Update(KinectBodies kinectBodies)
        {
            lock (_object)
            {
                if (kinectBodies.Body.Count <= 0)
                {
                    Humans.Clear();
                    return;
                }
                var keys = Humans.Select(s => s.Body.TrackingId).ToList();
                var bodyIds = kinectBodies.Body.Select(s => s.TrackingId).ToList();

                // Remove those humans that dont exist in the list of kinect bodies anymore
                foreach (var key in keys)
                {
                    if (!bodyIds.Contains(key))
                    {
                        var item = Humans.FirstOrDefault(s => s.Body.TrackingId == key);
                        if (item != null)
                        {
                            //item.Gestures.CollectionChanged -= GesturesCollectionChanged;
                            Humans.Remove(item);
                            Log.InfoFormat("Removed human: {0}", item.Id);
                        }
                    }
                }

                foreach (var kinectBody in kinectBodies.Body)
                {
                    var item = Humans.FirstOrDefault(s => s.Body.TrackingId == kinectBody.TrackingId);
                    if (item == null)
                    {
                        var human = new Human(kinectBody.TrackingId, _motionModules)
                        {
                            Body = kinectBody
                        };
                        //human.Gestures.CollectionChanged += GesturesCollectionChanged;
                        Humans.Add(human);
                        Log.InfoFormat("Added new human: {0}", human.Id);
                    }
                    else
                    {
                        if (!kinectBody.IsTracked)
                        {
                            Humans.Remove(item);
                            Log.InfoFormat("Removed untracked human: {0}", item.Id);
                        }
                        else
                        {
                            item.Body = kinectBody;
                        }
                    }
                }
            }
        }

        void GesturesCollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e)
        {
            //Log.InfoFormat("Gesture collection changed : {0}", sender.ToString());
            if (e.Action == NotifyCollectionChangedAction.Add)
            {
                //Log.InfoFormat("Gesture collection changed : {0}", sender.ToString());
                if (e.NewItems != null && e.NewItems.Count > 0)
                {
                    var item = e.NewItems[0] as Gesture;
                    if (item != null)
                    {
                        lock (_object)
                        {
                            if (_behaviorModules != null && _behaviorModules.Count > 0)
                            {
                                var module = _behaviorModules[0];
                                if (module != null)
                                {
                                    var jobKey = JobKey.Create(string.Format("Task{0}", item.Name), "MainGroup");
                                    var factory = TinyIoCContainer.Current.Resolve<StdSchedulerFactory>();
                                    IScheduler scheduler = null;
                                    if (factory != null)
                                    {
                                        scheduler = factory.GetScheduler();
                                    }
                                    if (!scheduler.CheckExists(jobKey))
                                    {
                                        IJobDetail detail = JobBuilder.Create<SimpleBehaviorTask>()
                                            .WithIdentity(jobKey)
                                            .Build();

                                        detail.JobDataMap.Add("BehaviorServerIp", module.responder.Host);
                                        detail.JobDataMap.Add("BehaviorServerPort", module.responder.Port);
                                        detail.JobDataMap.Add("BehaviorName", "wish");
                                        //detail.JobDataMap.Add("BehaviorName", "greet");

                                        ITrigger trigger = TriggerBuilder.Create().ForJob(detail).StartNow().Build();
                                        scheduler.ScheduleJob(detail, trigger);
                                        Log.InfoFormat("New job about to be scheduled: {0}", jobKey.Name);
                                    }
                                    else
                                    {
                                        Log.Info("Job already active");
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        public void Update(GestureTriggers triggers)
        {
            //Log.Info("Gesture Update");
            if (triggers != null)
            {
                lock (_object)
                {
                    //if
                    var item = _humans.FirstOrDefault(s => s.Body.TrackingId == triggers.id);
                    if (item != null)
                    {
                        //Log.InfoFormat("Gesture Update: {0} : {1}", triggers.id, triggers.motion.Count);
                        foreach (var trigger in triggers.motion)
                        {
                            var gest = item.Gestures.FirstOrDefault(g => g.Name == trigger.name);

                            if (gest != null && !string.IsNullOrEmpty(trigger.name))
                            {
                                gest.Refresh(trigger);
                            }
                            else
                            {
                                if (!string.IsNullOrEmpty(trigger.name))
                                {
                                    var newGest = new Gesture();
                                    newGest.Refresh(trigger);
                                    item.Gestures.Add(newGest);
                                }
                            }
                            
                        }

                        //if (gest != null)
                        //{
                        //    if (trigger.motion.confidence < 85 || !trigger.motion.active)
                        //    {
                        //        item.Gestures.Remove(gest);
                        //        Log.InfoFormat("Gesture Removed: {0}",trigger.motion.name);
                        //    }
                        //    else
                        //    {
                        //        //gest = new Gesture
                        //        //{
                        //        //    Name = trigger.motion.name,
                        //        //    Mode = (GestureMode) trigger.motion.type
                        //        //};
                        //    }
                        //}
                        //else
                        //{
                        //    if (trigger.motion.confidence > 95 || trigger.motion.active)
                        //    {
                        //        item.Gestures.Add(new Gesture
                        //        {
                        //            Name = trigger.motion.name,
                        //            Mode = (GestureMode) trigger.motion.type
                        //        });
                        //        Log.InfoFormat("Gesture Added: {0}", trigger.motion.name);
                        //    }
                        //}


                    }
                }
            }
        }

        public void RegisterMotionRecognitionModule(experimot.msgs.GestureRecognitionModule module)
        {
            if (module != null && !string.IsNullOrEmpty(module.name))
            {
                lock (_object)
                {
                    var regMod = _motionModules.FirstOrDefault(s => s.Name == module.name);
                    if (regMod == null)
                    {
                        _motionModules.Add(new GestureModule(module));
                    }
                    else
                    {
                        regMod = new GestureModule(module);
                    }
                }
            }
        }

        public void RegisterRobotBehaviorModule(experimot.msgs.RobotBehaviorModule module)
        {
            if (module != null && !string.IsNullOrEmpty(module.name))
            {
                lock (_object)
                {
                    var regMod = _behaviorModules.FirstOrDefault(s => s.name == module.name);
                    if (regMod == null)
                    {
                        _behaviorModules.Add(module);
                    }
                    else
                    {
                        regMod = module;
                    }
                }
            }
        }
    }
}
