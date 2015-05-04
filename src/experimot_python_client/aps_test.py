from pytz import utc

from apscheduler.schedulers.background import BackgroundScheduler
#from apscheduler.jobstores.sqlalchemy import SQLAlchemyJobStore
from apscheduler.executors.pool import ThreadPoolExecutor, ProcessPoolExecutor

def myfunc():
    print "Hello, this is my function"

#jobstores = {
#    'default': SQLAlchemyJobStore(url='sqlite:///jobs.sqlite')
#}
executors = {
    'default': ThreadPoolExecutor(20),
    'processpool': ProcessPoolExecutor(5)
}
job_defaults = {
    'coalesce': False,
    'max_instances': 3
}
#scheduler = BackgroundScheduler(jobstores=jobstores, executors=executors, job_defaults=job_defaults, timezone=utc)
scheduler = BackgroundScheduler(executors=executors, job_defaults=job_defaults, timezone=utc)
job = scheduler.add_job(myfunc, 'interval', minutes=1)

scheduler.start()