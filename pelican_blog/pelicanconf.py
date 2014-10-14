#!/usr/bin/env python
# -*- coding: utf-8 -*- #
from __future__ import unicode_literals

AUTHOR = u'\u4e5d\u54e5'
SITENAME = u'\u4e5d\u54e5\u7684\u90e8\u843d'
SITEURL = ''

PATH = 'content'

TIMEZONE = 'Asia/Chongqing'

DEFAULT_LANG = u'cn'

# Feed generation is usually not desired when developing
FEED_ALL_ATOM = None
CATEGORY_FEED_ATOM = None
TRANSLATION_FEED_ATOM = None

# Blogroll
#LINKS = (('Pelican', 'http://getpelican.com/'),
#         ('Python.org', 'http://python.org/'),
#         ('Jinja2', 'http://jinja.pocoo.org/'),
#         ('You can modify those links in your config file', '#'),)

# Social widget
SOCIAL = (('github', 'http://github.com/zouivex'),)

DEFAULT_PAGINATION = 10

# Uncomment following line if you want document-relative URLs when developing
#RELATIVE_URLS = True

# static paths will be copied without parsing their contents
STATIC_PATHS = [
    'images',
    'extra/CNAME'
    ]

# Same as Octopress structure
ARTICLE_URL = 'blog/{date:%Y}/{date:%m}/{date:%d}/{slug}/'
ARTICLE_SAVE_AS = 'blog/{date:%Y}/{date:%m}/{date:%d}/{slug}/index.html'

# Extract metadata from file name
FILENAME_METADATA = '(?P<date>\d{4}-\d{2}-\d{2})_(?P<slug>.*)'

# Use totally new generated files each time
DELETE_OUTPUT_DIRECTORY = True

# Make blog more beautiful
TYPOGRIFY = True

# This is a single author site
AUTHOR_URL = ''
AUTHOR_SAVE_AS = ''

# Theme
THEME = 'theme/pelican-bootstrap3-lovers'
BOOTSTRAP_THEME = 'lovers'

HEADER_IMAGE = "yourheaderimage.png"

# Plugins
#PLUGIN_PATHS = ["plugins"]
#PLUGINS = ["assets", "liquid_tags", "sitemap"]

DISQUS_SITENAME = 'httpzouivexgithubio'

TAG_CLOUD = True

ABOUT_ME = 'Whatever you want to say about yourself'