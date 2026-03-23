# -*- python -*-
# buildbot.tac for Buildbot Worker

import os
from twisted.application import service
from buildbot_worker.bot import Worker

# Get configuration from environment variables
master_host = os.environ.get('BUILDBOT_MASTER_HOST', 'buildbot')
master_port = int(os.environ.get('BUILDBOT_MASTER_PORT', '9989'))
name = os.environ.get('WORKERNAME', 'worker')
passwd = os.environ.get('WORKERPASS', 'pass')
basedir = os.environ.get('WORKER_BASEDIR', '/worker')

application = service.Application('buildbot-worker')
worker = Worker(master_host, master_port, name, passwd, basedir, 600, True)
worker.setServiceParent(application)
