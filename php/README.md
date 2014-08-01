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
	gt1.user=test1
	gt1.password=test1
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
	
Create demo user
----------------
	<?php
		$gt = new GT1();
		$xml = $gt->demo("test");
		$rev = $gt->result($xml);
		print_r($rev);
	
	Array
	(
		[Code] => AMS_OK
		[Login] => 35000294
		[Pwd] => 1234qwer
		[Email] => NULL
	)

Create real user
----------------
	<?php
		$gt = new GT1();
		$gt->login();
		$xml = $gt->real("aaa");
		$rev = $gt->result($xml);
		print_r($rev);

	Array
	(
		[Code] => AMS_OK
		[Login] => 30000671
		[Pwd] => WZ300Ifi
		[Email] => NULL
	)
	