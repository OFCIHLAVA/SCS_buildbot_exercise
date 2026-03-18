FROM python:3-alpine

RUN apk add --no-cache \
    build-base \
    gcc \
    libffi-dev \
    openssl-dev \
    su-exec

ENV BUILDBOT_WORKER_VERSION=4.3.0
RUN pip3 --no-cache-dir install --upgrade pip && pip3 --no-cache-dir install \
    buildbot-worker==$BUILDBOT_WORKER_VERSION

RUN adduser -h /worker -D buildbot
WORKDIR /worker

VOLUME /worker

COPY worker.buildbot.tac /worker/buildbot.tac

## USER buildbot

CMD ["twistd", "--pidfile=", "--nodaemon", "--python=/worker/buildbot.tac"]
