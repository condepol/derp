#!/usr/bin/env perl

use strict;
use Net::DBus qw(:typing);
my $bus = Net::DBus->session;
my $svc = $bus->get_service("org.freedesktop.Notifications");
my $obj = $svc->get_object("/org/freedesktop/Notifications");
$obj->Notify("helo",0,"gtk-dialog-info","lolk","blah",[],{0,0,0},5000);
