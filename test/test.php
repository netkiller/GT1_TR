<?php
$gt = new GT1();
print_r($gt);
$proto = $gt->demo("test");
print_r($proto);
printf("=========================================\n");
print_r($gt->login());
print_r($gt);
printf("=========================================\n");
$login = $gt->login('test2','abcd1234');
print_r($gt);
print_r($login);
printf("=========================================\n");
