import time

class PeopleTracker:
    def __init__(self, tracker, memory, distanceX, distanceY, angleWz):
        self.tracker = tracker
        self.memory = memory
        self.mode = "Move"
        self.targetName = "People"
        self.distanceX = distanceX
        self.distanceY = distanceY
        self.angleWz = angleWz
        self.thresholdX = 0.2
        self.thresholdY = 0.1
        self.thresholdWz = 0.3
        self.effector = "None"
        self.subscribeDone = False
        self.isRunning = False
        self.targetLost = False
        self.targetReached = False

    def getName(self):
        return "ExperimotPeopleTracker"

    def initialize(self):
        #self.BIND_PYTHON(self.getName(), "setParameter")
        #self.BIND_PYTHON(self.getName(), "onTargetLost")
        #self.BIND_PYTHON(self.getName(), "onTargetReached")
        #self.BIND_PYTHON(self.getName(), "onTargetChanged")
        self.memory.subscribeToEvent("ALTracker/ActiveTargetChanged", self.getName(), "onTargetChanged")

    def uninitialize(self):
        if self.subscribeDone:
            self.memory.unsubscribeToEvent("ALTracker/TargetLost", self.getName())
            self.memory.unsubscribeToEvent("ALTracker/TargetReached", self.getName())
            self.subscribeDone = False

        if self.isRunning:
            self.tracker.setEffector("None")
            self.tracker.stopTracker()
            self.tracker.unregisterTarget(self.targetName)
            self.isRunning = False

    def start(self):
        self.memory.subscribeToEvent("ALTracker/TargetLost", self.getName(), "onTargetLost")
        self.memory.subscribeToEvent("ALTracker/TargetReached", self.getName(), "onTargetReached")
        self.subscribeDone = True

        #mode = self.getParameter("Mode")
        #self.distanceX = self.getParameter("Distance X (m)")
        #self.thresholdX = self.getParameter("Threshold X (m)")
        #self.distanceY = self.getParameter("Distance Y (m)")
        #self.thresholdY = self.getParameter("Threshold Y (m)")
        #self.angleWz = self.getParameter("Theta (rad)")
        #self.thresholdWz = self.getParameter("Threshold Theta (rad)")
        #self.effector = self.getParameter("Effector")

        self.tracker.setEffector(self.effector)

        peopleIds = []

        self.tracker.registerTarget(self.targetName, peopleIds)
        self.tracker.setRelativePosition([-self.distanceX, self.distanceY, self.angleWz,
                                           self.thresholdX, self.thresholdY, self.thresholdWz])
        self.tracker.setMode(self.mode)

        self.tracker.track(self.targetName) #Start tracker
        self.isRunning = True

    def stop(self):
        #self.onStopped()
        #self.onUnload()
        self.uninitialize()

    def onInput_peopleId(self, p):
        if(p is None):
            return

        self.tracker.registerTarget(self.targetName, p)

    #def setParameter(self, parameterName, newValue):
    #    GeneratedClass.setParameter(self, parameterName, newValue)
    #    if (parameterName == 'Mode'):
    #        self.tracker.setMode(newValue)
    #        return

    #    if (parameterName == "Distance X (m)"):
    #        self.distanceX = newValue
    #        self.tracker.setRelativePosition([-self.distanceX, self.distanceY, self.angleWz,
    #                                           self.thresholdX, self.thresholdY, self.thresholdWz])
    #        return

    #    if (parameterName == "Distance Y (m)"):
    #        self.distanceY = newValue
    #        self.tracker.setRelativePosition([-self.distanceX, self.distanceY, self.angleWz,
    #                                           self.thresholdX, self.thresholdY, self.thresholdWz])
    #        return

    #    if (parameterName == "Theta (rad)"):
    #        self.angleWz = newValue
    #        self.tracker.setRelativePosition([-self.distanceX, self.distanceY, self.angleWz,
    #                                           self.thresholdX, self.thresholdY, self.thresholdWz])
    #        return

    #    if (parameterName == "Threshold X (m)"):
    #        self.thresholdX = newValue
    #        self.tracker.setRelativePosition([-self.distanceX, self.distanceY, self.angleWz,
    #                                           self.thresholdX, self.thresholdY, self.thresholdWz])
    #        return

    #    if (parameterName == "Threshold Y (m)"):
    #        self.thresholdY = newValue
    #        self.tracker.setRelativePosition([-self.distanceX, self.distanceY, self.angleWz,
    #                                           self.thresholdX, self.thresholdY, self.thresholdWz])
    #        return

    #    if (parameterName == "Threshold Theta (rad)"):
    #        self.thresholdWz = newValue
    #        self.tracker.setRelativePosition([-self.distanceX, self.distanceY, self.angleWz,
    #                                           self.thresholdX, self.thresholdY, self.thresholdWz])
    #        return

    #    if(parameterName == "Effector"):
    #        self.tracker.setEffector(newValue)
    #        self.effector = newValue
    #        return

    def onTargetLost(self, key, value, message):
        #self.targetLost()
        print "Target Lost"
        self.targetLost = True;

    def onTargetReached(self, key, value, message):
        #self.targetReached()
        print "Target Reached"
        self.targetReached = True;

    def getTargetReached(self):
        return self.targetReached

    def getTargetLost(self):
        return self.targetLost

    def onTargetChanged(self, key, value, message):
        if value == self.targetName and not self.subscribeDone:
            self.memory.subscribeToEvent("ALTracker/TargetLost", self.getName(), "onTargetLost")
            self.memory.subscribeToEvent("ALTracker/TargetReached", self.getName(), "onTargetReached")
            self.subscribeDone = True
        elif value != self.targetName and self.subscribeDone:
            self.memory.unsubscribeToEvent("ALTracker/TargetLost", self.getName())
            self.memory.unsubscribeToEvent("ALTracker/TargetReached", self.getName())
            self.subscribeDone = False