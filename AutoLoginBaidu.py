#! /usr/bin/env python
#coding: utf-8


import urllib
import urllib2
import cookielib

class Loginer(object):
	"""Auto login Baidu WebSite"""
	def __init__(self, user,passwd):
		super(Loginer, self).__init__()
		self.user = user
		self.passwd = passwd
		self.cj = cookielib.CookieJar()
		self.opener = urllib2.build_opener(
			urllib2.HTTPRedirectHandler(),
			urllib2.HTTPHandler(debuglevel=0),
			urllib2.HTTPSHandler(debuglevel=0),
			urllib2.HTTPCookieProcessor(self.cj))
		self.opener.addheaders = [
			('User-agent', ('Mozilla/4.0 (compatible; MSIE 6.0; '
							'Windows NT 5.2; .NET CLR 1.1.4322'))]

	def LoginToBaidu(self):
		login_data = urllib.urlencode({'login_field' : self.user, 'password' : self.passwd})
		print login_data
		response = self.opener.open("https://github.com/login", login_data)
		return ''.join(response.readlines())
 
def main():
	"""Main function for case test"""
	loginer = Loginer("xxxxxxxx", "yyyyyyyyy")
	print loginer.LoginToBaidu()

if __name__ == '__main__':
	main()
