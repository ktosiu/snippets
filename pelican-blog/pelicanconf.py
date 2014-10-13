#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

# Basic settings

AUTHOR = u'九哥'
SITENAME = u'九哥的部落'
SITESUBTITLE = u'技术、阅读、生活'

# Not set for local use
SITEURL = ''

# Set for FEED
FEED_DOMAIN = SITEURL
FEED_ATOM = 'feeds/atom.xml'
FEED_ALL_ATOM = 'feeds/all.atom.xml'
CATEGORY_FEED_ATOM = 'feeds/%s.atom.xml'

# Custom items in main menu
MENUITEMS = [('首页', '/index.html'),
			 ('存档', '/archives.html')]

# Search box
SEARCH_BOX = True

# Path to content directory to be processed by Pelican. If undefined, 
# and content path is not specified via an argument to the pelican command, 
# Pelican will use the current working directory.
PATH = 'content'

# A list of directories to look at for pages, relative to PATH.
PAGE_PATHS = ['pages']

TIMEZONE = 'Asia/Chongqing'

# If set to True, several typographical improvements will be incorporated 
# into the generated HTML via the Typogrify library, 
# which can be installed via: pip install typogrify
TYPOGRIFY = True

DEFAULT_LANG = u'cn'

# static paths will be copied without parsing their contents
STATIC_PATHS = [
    'images',
    'extra/CNAME'
    ]

EXTRA_PATH_METADATA = {'extra/CNAME': {'path': 'CNAME'},}

DELETE_OUTPUT_DIRECTORY = True

# Feed generation is usually not desired when developing
FEED_ALL_ATOM = None
CATEGORY_FEED_ATOM = None
TRANSLATION_FEED_ATOM = None

# URL settings
ARTICLE_URL = 'posts/{date:%Y}/{date:%b}/{date:%d}/{slug}/'
ARTICLE_SAVE_AS = 'posts/{date:%Y}/{date:%b}/{date:%d}/{slug}/index.html'

# Yearly monthly archive
YEAR_ARCHIVE_SAVE_AS = 'posts/{date:%Y}/index.html'
MONTH_ARCHIVE_SAVE_AS = 'posts/{date:%Y}/{date:%b}/index.html'


DEFAULT_PAGINATION = 5

# Uncomment following line if you want document-relative URLs when developing
#RELATIVE_URLS = True

# For Tag Cloud
TAG_CLOUD_STEPS = 4	      #Count of different font sizes in the tag cloud.
TAG_CLOUD_MAX_ITEMS = 100 #Maximum number of tags in the cloud.

#Order archives by newest first by date. (False: orders by date with older articles first.)
NEWEST_FIRST_ARCHIVES = True

# Themes

PLUGINS = ['summary', 'liquid_tags.img', 'liquid_tags.video',
           'liquid_tags.include_code', 'liquid_tags.notebook',
           'liquid_tags.literal']
           
# Theme to use to produce the output. 
# Can be a relative or absolute path to a theme folder, or
# the name of a default theme or a theme installed via pelican-themes (see below).
#
# THEME = 'simple'
THEME = 'themes/pelican-octopress-theme'

# Destination directory in the output path where Pelican will place the files 
# collected from THEME_STATIC_PATHS. Default is theme.
HEME_STATIC_DIR = 'theme'	

# Static theme paths you want to copy. Default value is static, 
# but if your theme has other static paths, you can put them here. 
# If files or directories with the same names are included in the paths defined in this settings, 
# they will be progressively overwritten.
THEME_STATIC_PATHS = ['static']	

# Specify the CSS file you want to load.
CSS_FILE = 'main.css'

# Side bar image
#SIDEBAR_IMAGE = 'images/9_logo.png'

DISPLAY_CATEGORIES_ON_MENU = True

# Setup for GITHUB
#GITHUB_USER = 'zouivex@gmail.com'
#GITHUB_REPO_COUNT = 5
#GITHUB_SKIP_FORK = False

# GOOGLE_PLUS
GOOGLE_PLUS_ID = 'zouivex@gmail.com'
#GITHUB_SHOW_USER_LINK = True

# Social widget
SOCIAL = (('Email', 'zouivex@gmail.com'),)

# Blogroll
LINKS = (('Pelican', 'http://getpelican.com/'),
         ('Python.org', 'http://python.org/'),
         ('Jinja2', 'http://jinja.pocoo.org/'))
