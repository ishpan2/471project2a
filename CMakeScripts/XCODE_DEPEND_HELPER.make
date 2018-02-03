# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.lab3.Debug:
/Users/ip/Documents/cs471/lab3/lab03/Debug/lab3:\
	/usr/local/lib/libglfw.3.2.dylib
	/bin/rm -f /Users/ip/Documents/cs471/lab3/lab03/Debug/lab3


PostBuild.lab3.Release:
/Users/ip/Documents/cs471/lab3/lab03/Release/lab3:\
	/usr/local/lib/libglfw.3.2.dylib
	/bin/rm -f /Users/ip/Documents/cs471/lab3/lab03/Release/lab3


PostBuild.lab3.MinSizeRel:
/Users/ip/Documents/cs471/lab3/lab03/MinSizeRel/lab3:\
	/usr/local/lib/libglfw.3.2.dylib
	/bin/rm -f /Users/ip/Documents/cs471/lab3/lab03/MinSizeRel/lab3


PostBuild.lab3.RelWithDebInfo:
/Users/ip/Documents/cs471/lab3/lab03/RelWithDebInfo/lab3:\
	/usr/local/lib/libglfw.3.2.dylib
	/bin/rm -f /Users/ip/Documents/cs471/lab3/lab03/RelWithDebInfo/lab3




# For each target create a dummy ruleso the target does not have to exist
/usr/local/lib/libglfw.3.2.dylib:
