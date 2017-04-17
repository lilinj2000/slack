AUTOMAKE_OPTIONS = foreign

bin_PROGRAMS = slack
slack_SOURCES = \
	Config.cc \
	Server.cc \
	Main.cc

slack_CPPFLAGS =  \
		$(BOOST_CPPFLAGS) \
		$(SOIL_CPPFLAGS) \
		$(SEA_CPPFLAGS) \
		$(AIR_CPPFLAGS)


slack_LDADD = \
	$(BOOST_LIBADD) \
	$(SOIL_LIBADD) \
	$(SEA_LIBADD) \
	$(AIR_LIBADD)


slack_LDFLAGS = $(LIBADD_DL) -Wl,--no-as-needed -pthread

# header files
noinst_HEADERS = Config.hh \
	Server.hh \
	Log.hh

EXTRA_DIST = env.sh slack.cfg log.cfg

slackdir = $(bindir)
slack_DATA = $(EXTRA_DIST)

