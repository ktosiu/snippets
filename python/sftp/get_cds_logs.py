#!/bin/env python

import os
import sys
import shutil
import pysftp

remote_hosts = {
    '10.117.171.13': ('root', 'Reuters1'),
    '10.117.171.14': ('root', 'Reuters1'),
    '10.117.171.15': ('root', 'Reuters1'),
    '10.117.171.16': ('root', 'Reuters1'),
    '10.117.171.17': ('root', 'Reuters1'),
    '10.117.171.18': ('root', 'Reuters1')
}

interested_paths = {
    #'events': '/data/cds/events',
    #'stats': '/data/cds/stats',
    #'pcaps': '/data/cds/pcap'
    'events': '/data/cds/events',
    'pcaps': '/data/cds/pcap'
}

local_root_path = '/root/sit_logs'

def main():
    prepare_local_path()
    get_files_from_all_remote_hosts()

def prepare_local_path():
    if not os.path.exists(local_root_path):
        os.mkdir(local_root_path)
    else:
        shutil.rmtree(local_root_path)
        os.mkdir(local_root_path)

def get_files_from_all_remote_hosts():
    for hostname, profile in remote_hosts.iteritems():
        username = profile[0]
        password = profile[1]
        print 'Processing host: ' + hostname
        get_interested_files(hostname, username, password)

def get_interested_files(hostname, name, passwd):
    with pysftp.Connection(hostname, username=name, password=passwd) as sftp:
        for key, path in interested_paths.iteritems():
            print 'Copying ' + key
            local_path = local_root_path + '/' + hostname
            if not os.path.exists(local_path):
                os.mkdir(local_path)
            try:
                sftp.get_d(path, local_path, preserve_mtime=True)
            except:
                print 'Fail to copy ' + path

if __name__ == '__main__':
    sys.exit(main())
