<?php
$mtf = new MTF();
//print_r($mtf);
$proto = $mtf->demo("test");
print_r($proto);
$rev = $mtf->result($proto);
print_r($rev);
printf("=========================================\n");
$login = $mtf->login();
//print_r($mtf);
printf("=========================================\n");
//$login = $mtf->login('hxpm2','1234qwer');
print_r($mtf->result($login));
printf("=========================================\n");
$html = $mtf->real("aaa");
print_r($html);
//printf("=========================================\n");
$rev = $mtf->result($html);
print_r($rev);
//printf("=========================================\n");
$html = $mtf->transfer($rev['Login'],'120.50','Currency:USD;DEPOSI:902140318J017');
print_r($mtf->result($mtf->balance($rev['Login'])));
//$html = $mtf->transfer('30000689','120.50','Currency:USD;DEPOSI:902140318J017');
//printf("=========================================\n");
//print_r($mtf->result($mtf->balance('30000689')));
//echo $mtf->debug;
//print_r($mtf->change_password('30000696','abc123', 'jkjk9898'));

