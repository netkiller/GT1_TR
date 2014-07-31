GT1 PHP extension
================

	# /srv/php/bin/phpize 
	# ./configure --enable-gt1 --with-php-config=/srv/php/bin/php-config
	# make
	# make install
	
	# cat > /srv/php/etc/conf.d/gt1.ini <<PHP
	extension=gt1.so
	[GT1]
	gt1.url=http://59.152.226.199:3355
	gt1.demo.user=test1
	gt1.demo.pass=test1
	gt1.real.user=test1
	gt1.real.pass=test1
	PHP	

Check 
=====
	# php --ri gt1

	gt1

	gt1 support => enabled
	
Test
====
	# php -d"extension=gt1.so" -m	
	# php -r "hello();"