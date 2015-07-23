using Indriya.Core;
using System.Globalization;
using KinectEx.Smoothing;
using System.Linq;
using System;
using System.Collections.Generic;
using System.Reflection;
using Indriya.Core.Msgs;
using Newtonsoft.Json.Linq;

#if USE_KINECT_BODIES
#else
using KinectEx;
#endif

// ReSharper disable LoopCanBeConvertedToQuery

namespace Indriya.Kinect.Perception
{
    public class MethodArg
    {
        private MethodInfo _methodInfo;
        private List<object> _args;

        private MethodArg()
        {
            _args = new List<object>();
        }

        public static MethodArg Create(string methodName, string argValues)
        {

            MethodArg ret = null;
#if USE_KINECT_BODIES
            
#else
            if (!string.IsNullOrEmpty(methodName) && !string.IsNullOrEmpty(argValues))
            {
                var methods = typeof (BodyExtensions).GetMethods(
                    BindingFlags.Static | BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
                var vals = argValues.Split(',');
                var method = methods.Where(s => s.Name == methodName);
                foreach (var methodInfo in method)
                {
                    var parameters = methodInfo.GetParameters().ToList();
                    if (parameters.Count > 0 && parameters.Count-1 == vals.Count())
                    {
                        if (parameters[0].ParameterType.Name == "IBody")
                        {
                            List<object> arguments = new List<object>();
                            int i = 1;
                            foreach (var val in vals)
                            {
                                var conv = Dynamitey.Dynamic.InvokeConvert(val.Trim(), parameters[i++].ParameterType);
                                arguments.Add(conv);
                            }
                            ret = new MethodArg();
                            ret._methodInfo = methodInfo;
                            ret._args = arguments;
                            break;
                        }
                    }
                }
            }
#endif
            return ret;
        }

        public double Invoke(object obj, double defaultValue)
        {
            if (_methodInfo != null)
            {
                double ret;
                var newArgs =new List<object>();
                newArgs.Add(obj);
                newArgs.AddRange(_args);
                if (double.TryParse(_methodInfo.Invoke(obj, newArgs.ToArray()).ToString(), out ret))
                {
                    return ret;
                }
            }
            return defaultValue;
        }
    }

    public class NaoJoint
    {
        private string _sid;
        private string _name;
        private double _min;
        private double _max;
        private double _zero;
        public double _mid;
        private MethodArg _methodArg;

        public MethodArg KinectMapMethod
        {
            get { return _methodArg; }
            set { _methodArg = value; }
        }

        public double Mid
        {
            get { return _mid; }
        }

        public string Name
        {
            get { return _name; }
        }

        public static NaoJoint FromJsonTokens(JToken jointObj, JToken mapObject)
        {
            NaoJoint ret = null;
            if (jointObj != null)
            {
                ret = new NaoJoint
                {
                    _sid = jointObj.Value<string>("sid"),
                    _name = jointObj.Value<string>("name"),
                    _min = jointObj.SelectToken("$.limits").Value<double>("min"),
                    _max = jointObj.SelectToken("$.limits").Value<double>("max"),
                    _zero = jointObj.Value<double>("zeroPosition"),
                    _mid = jointObj.Value<double>("middlePosition")
                };
                if (mapObject != null)
                {
                    var kinect = mapObject.Value<object>("kinect");
                    if (kinect != null)
                    {
                        var kinObj = mapObject.SelectToken("$.kinect");
                        if (kinObj != null && kinObj.HasValues)
                        {
                            ret._methodArg = MethodArg.Create(kinObj.Value<string>("method"),
                                kinObj.Value<string>("arg"));
                        }
                    }
                }
            }
            return ret;
        }

        public double ScaleToNao(double humanMin, double humanMax, double humanValue)
        {
            var humanRange = humanMax - humanMin;
            var naoRange = _max - _min;
            if (humanValue > humanMax)
                humanValue = humanMax;
            else if (humanValue < humanMin)
                humanValue = humanMin;
            var diff = humanValue - humanMin;
            var newValue = _max - ((diff/humanRange)*naoRange);
            return newValue*Math.PI/180.0;
        }
    }

    /// <summary>
    /// Interaction logic for MainWindow
    /// </summary>
    public class NaoJointPublisher : MessagePublisher<ParamList>
    {
        private readonly List<NaoJoint> _joints;

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public NaoJointPublisher()
            : this("tcp://*", 5592, "NJP", string.Empty, string.Empty)
        {
        }

        /// <summary>
        /// Initializes a new instance of the MainWindow class.
        /// </summary>
        public NaoJointPublisher(string host, uint port, string topic, string naoJointsJson, string naoKinectJson)
            : base(host, port, topic)
        {
            _joints = new List<NaoJoint>();
            if (!string.IsNullOrEmpty(naoJointsJson) && !string.IsNullOrEmpty(naoKinectJson))
            {
                var naoObj = JArray.Parse(naoJointsJson);
                var kinectObj = JArray.Parse(naoKinectJson);

                foreach (var naoItem in naoObj)
                {
                    var kinectItem =
                        kinectObj.FirstOrDefault(s => s.Value<string>("sid") == naoItem.Value<string>("sid"));
                    _joints.Add(NaoJoint.FromJsonTokens(naoItem, kinectItem));
                }
            }
        }

        public List<NaoJoint> Joints
        {
            get { return _joints; }
        }

        /// <summary>
        /// Check if the instance of human is valid
        /// </summary>
        /// <param name="msg"></param>
        /// <returns></returns>
        protected override bool IsValid(ParamList msg)
        {
            return msg != null && msg.param.Count > 0;
        }

        public ParamList GetJointValues(SmoothedBody<ExponentialSmoother> body)
        {
            var list = new ParamList();
            if (body != null && _joints != null && _joints.Count > 0)
            {
                var validJoints = _joints.Where(s => s.KinectMapMethod != null);
                foreach (var naoJoint in validJoints)
                {
                    var result = naoJoint.KinectMapMethod.Invoke(body, naoJoint.Mid);
                    list.param.Add(new Param()
                    {
                        key = naoJoint.Name,
                        value = naoJoint.ScaleToNao(20, 170, result).ToString(CultureInfo.InvariantCulture)
                    });
                }
            }
            return list;
        }
    }
}
