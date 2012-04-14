#!/bin/sh

D=`dirname $0`
SBCL_HOME=`(cd $D; pwd)` $D/sbcl --core $D/sbcl-dist.core --load $D/asdf.fasl --userinit $D/sbclrc

