#!/usr/bin/env python

import sys
try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree as ET

smf_data_path = '/data/smf/data/smf-configuration.xml'

def main():
    remove_cds_from_smf_configuration()

def remove_cds_from_smf_configuration():
    smf_config = ET.ElementTree(file=smf_data_path)
    smf_config_root = smf_config.getroot()
    for node in smf_config_root.getiterator():
        if node.tag == 'Applications':
            for application in node.getiterator():
                if application.findtext('Name') == 'CDS':
                    node.remove(application)

    smf_config.write(smf_data_path)

if __name__ == '__main__':
    sys.exit(main())
