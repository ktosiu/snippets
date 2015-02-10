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

#remote_hosts = {
#    '10.117.171.13': ('root', 'Reuters1'),
#    '10.117.171.14': ('root', 'Reuters1')
#}

interested_paths = {
    'events': '/data/cds/events'
    #'stats': '/data/cds/stats',
    #'statsrecovery': '/data/cds/statsrecovery'
    #'cachedump': '/data/cds/realtimecache'
    #'pcaps': '/data/cds/pcap'
    #'events': '/data/cds/events'
    #'pcaps': '/data/cds/pcap'
    #'smflogs': '/data/smf/log'
}

local_root_path = '/root/cds_events'

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

            with sftp.cd(path):
                max_mtime = 0
                file_name = ''
                file_size = 0
                for attr in sftp.listdir_attr():
                    if attr.st_mtime > max_mtime:
                        max_mtime = attr.st_mtime
                        file_name = attr.filename
                        file_size = attr.st_size
                file_size = file_size / (1024.0 * 1024.0)
                str_file_size = '%.2f' % file_size
                log = 'Copy {0} ({1}M) to {2}'.format(file_name, str_file_size, local_path)
                print log
                try:
                    os.chdir(local_path)
                    sftp.get(file_name, preserve_mtime=True)
                except:
                    print 'Fail to copy ' + file_name

if __name__ == '__main__':
    sys.exit(main())
