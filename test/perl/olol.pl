#!/usr/bin/env perl
print "perl ?\n";
use Archive::Zip  qw( :ERROR_CODES :CONSTANTS );

$crc = Archive::Zip::computeCRC32( chr(1));
printf("%08x\n",$crc);
