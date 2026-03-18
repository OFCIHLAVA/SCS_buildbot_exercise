# SCS Build Engineer Take Home Assessment
# Do not distribute

FROM python:3-alpine

RUN apk add --no-cache \
    build-base \
    libffi-dev \
    openssl-dev \
    su-exec

ENV BUILDBOT_VERSION=4.3.0
RUN pip3 --no-cache-dir install --upgrade pip && pip3 --no-cache-dir install \
    buildbot[bundle,tls]==$BUILDBOT_VERSION

COPY master.buildbot.tac /var/lib/buildbot/buildbot.tac
COPY docker-entrypoint.sh /usr/local/bin/
COPY master.cfg /etc/buildbot/

RUN adduser -h /var/lib/buildbot -D buildbot
WORKDIR /var/lib/buildbot
RUN ln -s /etc/buildbot/master.cfg

VOLUME /var/lib/buildbot
EXPOSE 8010
EXPOSE 9989

## USER buildbot

ENTRYPOINT ["docker-entrypoint.sh"]
CMD ["twistd", "--pidfile=", "--nodaemon", "--python=buildbot.tac"]
