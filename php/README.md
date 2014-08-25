MTF PHP extension
================

	# /srv/php/bin/phpize 
	# ./configure --enable-mtf --with-php-config=/srv/php/bin/php-config
	# make
	# make install
	
	# cat > /srv/php/etc/conf.d/mtf.ini <<PHP
	extension=mtf.so
	[MTF]
	mtf.url=http://59.152.226.199:3355
	mtf.user=test1
	mtf.password=test1
	PHP	

Check 
=====
	# php --ri mtf

	mtf

	mtf support => enabled
	
Test
====
	# php -d"extension=mtf.so" -m	
	# php -r "hello();"
	
Create demo user
----------------
	<?php
		$gt = new MTF();
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
		$gt = new MTF();
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
	