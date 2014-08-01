<?php
$gt = new GT1();
//print_r($gt);
//$proto = $gt->demo("test");
//print_r($proto);
//printf("=========================================\n");
print_r($gt->login());
//print_r($gt);
//printf("=========================================\n");
$login = $gt->login('hxpm2','1234qwer');
print_r($gt);
print_r($login);
printf("=========================================\n");
$html = $gt->real("aaa");
print_r($html);
printf("=========================================\n");
$rev = $gt->result($html);
print_r($rev);