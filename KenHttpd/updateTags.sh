#!/bin/sh

rm ./#*  
rm *#

find . -name "*.[ch]pp" -print | xargs etags -a 





