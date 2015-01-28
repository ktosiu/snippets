#!/bin/env python

import os
import sys
import pysftp

remote_hosts = {
    '10.117.171.13': ('root', 'Reuters1'),
    '10.117.171.14': ('root', 'Reuters1'),
    '10.117.171.15': ('root', 'Reuters1'),
    '10.117.171.16': ('root', 'Reuters1'),
    '10.117.171.17': ('root', 'Reuters1'),
    '10.117.171.18': ('root', 'Reuters1')
}

filename = 'core_delay_server-release-1.00.07-1.x86_64.rpm'

def main():
    hostname = '10.117.171.13'
    profile = remote_hosts[hostname]
    username = profile[0]
    password = profile[1]
    put_interested_files(hostname, username, password)

def put_interested_files(hostname, name, passwd):
    with pysftp.Connection(hostname, username=name, password=passwd) as sftp:
       with sftp.cd('/tmp'):
           sftp.put(filename)

if __name__ == '__main__':
    sys.exit(main())
