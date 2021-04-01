#! /usr/bin/wish

listbox .list -yscroll \
".scroll set" -width 20 -height 20

pack .list -side left

scrollbar .scroll -command \
".list yview"

pack .scroll -side right -fill y

if {$argc > 0} {
  set dir [lindex $argv 0]
} else {
  set dir .
}

foreach i [exec ls -a $dir] {
  .list insert end "$i"
}

bind .list <Double-ButtonPress-1> {
  browse $dir [selection get]
}
bind all <Control-c> {destroy .}

proc browse {dir file} {
  if {$dir != "."} {
    set file $dir/$file
  }
  if [file isdirectory $file] {
    exec ./browse.tcl $file &
  } else {
    if [file isfile $file] {
      exec gvim $file &
	} else {
      error "can't browse $file"
	}
  }
}
