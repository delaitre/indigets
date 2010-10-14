TEMPLATE = subdirs
CONFIG += ordered
SUBDIRS = core \
    gics

gics.depends = core
