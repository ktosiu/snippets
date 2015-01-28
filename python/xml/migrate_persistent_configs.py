#!/usr/bin/env python

"""Script to migrate the configurations of previous version"""

import sys
import os
import subprocess
import xml.etree.ElementTree as ET
import logging

psdbin2xml = '/data/smf/bin/psdbin2xml '
HostManager = '/data/smf/bin/HostManager '

paths = {
    'cds_config_bin': '/data/smf/data/cdsconfig_previous.bin',
    'cds_config_xml': '/tmp/cdsconfig_previous.xml'
}

persistent_configs = {
    'enablenamemangling': '/config/enablenamemangling',
    'crashdumptype': '/config/crashdumptype',
    'ageoutdays':'/cache/ageoutdays',
    'ageouthours':'/cache/ageouthours',
    'ageoutminutes':'/cache/ageoutminutes',
    'ageoutchainsdays':'/cache/ageoutchainsdays',
    'ageoutchainshours':'/cache/ageoutchainshours',
    'ageoutchainsminutes':'/cache/ageoutchainsminutes',
    'ageoutchains':'/cache/ageoutchains',
    'ageout':'/cache/ageout'
}

persistent_config_values = {}

def set_up_logging():
    log_folder = '/tmp/migrate_persistent_configs/'
    if not os.path.exists(log_folder):
        os.makedirs(log_folder)
        
    log_file_name = log_folder + 'migrate_persistent_configs.log'
    if os.path.exists(log_file_name):
        os.remove(log_file_name)
    
    logging.basicConfig(filename=log_file_name,
                        level=logging.INFO,
                        format='%(asctime)s %(name)-12s %(levelname)-8s %(message)s')

def precondition_check():
    if not os.path.exists(paths['cds_config_bin']):
        logging.error(paths['cds_config_bin'] + ' does not exist! Fail to migrate persistent configs')
        sys.exit()

def run_command(cmd):
    logging.info('Run command: ' + cmd)
    process = subprocess.Popen(cmd.split(), stdout=subprocess.PIPE)
    out, err = process.communicate()
    return out

def get_persistent_values(node):
    for key, value in persistent_configs.iteritems():
        if node.attrib['Name'] == value:
            persistent_config_values[key] = node.attrib['Value']

def start_smf():
    """Start the smf service"""
    run_command('service smf start')

def check_start_smf():
    """If SMF is not started, then start it."""
    smf_status_string = run_command('service smf status')
    if smf_status_string != 'SMF is running':
        start_smf()

def write_smf_psd_integer(path, value):
    """Write integer value to PSD"""
    cmd = '{0} -writeparams {1}={2} as Integer'.format(HostManager, path, value)
    result = run_command(cmd)

def write_persistent_configs():
    for key, value in persistent_config_values.iteritems():
        write_smf_psd_integer(persistent_configs[key], value)

def get_persistent_configs():
    cmd_bin_to_xml = '{0} {1} {2} -v'.format(psdbin2xml, paths['cds_config_bin'], paths['cds_config_xml'])
    run_command(cmd_bin_to_xml)
    tree = ET.ElementTree(file=paths['cds_config_xml'])
    IntegerNodes = tree.findall(".//Integer")
    for iter in IntegerNodes:
        get_persistent_values(iter)
    os.remove(paths['cds_config_xml'])
    os.remove(paths['cds_config_bin'])

def main():
    set_up_logging()
    precondition_check()
    check_start_smf()
    get_persistent_configs()
    write_persistent_configs()
    logging.info('Succeed to migrate persistent configs.')

if __name__ == '__main__':
    sys.exit(main())
