<?php
$gt = new GT1();
//print_r($gt);
//$proto = $gt->demo("test");
//print_r($proto);
//$rev = $gt->result($proto);
//print_r($rev);
//printf("=========================================\n");
$login = $gt->login();
//print_r($gt);
//printf("=========================================\n");
//$login = $gt->login('hxpm2','1234qwer');
//print_r($gt->result($login));
//printf("=========================================\n");
//$html = $gt->real("aaa");
//print_r($html);
//printf("=========================================\n");
//$rev = $gt->result($html);
//print_r($rev);
//printf("=========================================\n");
//$html = $gt->transfer($rev['Login'],'120.50','Currency:USD;DEPOSI:902140318J017');
//$html = $gt->transfer('30000689','120.50','Currency:USD;DEPOSI:902140318J017');
//printf("=========================================\n");
//print_r($gt->result($gt->balance('30000689')));
//echo $gt->debug;
print_r($gt->change_password('30000696','abc123', 'jkjk9898'));

