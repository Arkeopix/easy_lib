#!/bin/sh
#
# Hook used to indent all source files before commiting
#

INDENT="indent"
ARGS="-nbad -bap -nbc -bbo -hnl -br -brs -c33 -cd33 -ncdb -ce -ci4 -cli0 -d0 -di1 -nfc1 -i8 -ip0 -l80 -lp -npcs -nprs -npsl -sai -saf -saw -ncs -nsc -sob -nfca -cp33 -ss -ts8 -il1"
if test ! -x "$INDENT"
then
    echo "Unable to find indent executable on the configuration."
    echo
    echo "Please configure it with :"
    echo " git config hooks.indent /path/to/indent"
    echo
fi

indent() {
	# getting against as the current commit
	if git rev-parse --verify HEAD >/dev/null 2>&1
	then
		local against=HEAD
	else
		# Initial commit: diff against an empty tree object
		local against=0f512a02d1a46b455299ce8c72fcc9ff70827951
	fi

	# loop on modified files
	git diff --cached --name-only $against | while read file;
	do
		local ext=$(expr "$file" : ".*\(\..*\)")
		case $ext in
		.c|.h)
			__indent_C;
		;;
		esac
	done
}

# Indent the file with `indent' if this is a C/H file
__indent_C() {
	if test ! -f $file
	then
		return;
	fi

	echo "Indenting " $file
	"$INDENT $ARGS" "$file"
	git add "$file"
}

indent
