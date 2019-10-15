#!/bin/sh

DEBUG=1
ROOT=.

# allow using these variables in sub-shels
export ROOT
export DEBUG


# TODO add_folder

add_file()
{
  # removing leading ./
  FOLDER_PATH="${0#./}"

  echo "    <folder path='$FOLDER_PATH'>" >> $ROOT/autogen.xml


  echo "      <file filename = `basename "$1"`>" >> $ROOT/autogen.xml
  # basename (without extension)
  echo "        <name>"`basename -s .png "$1"`"</name>" >> $ROOT/autogen.xml
  echo "      </file>" >> $ROOT/autogen.xml

  echo "    </folder>" >> $ROOT/autogen.xml
}


export -f add_file

# if [ !$1 ] ; then
#   echo "needed filename" ;
# fi

if [ $DEBUG = 1 ] ; then
  echo "inserting head"
fi

echo "<?xml version='1.0' encoding='utf-8'?>
<resources>
  <images>" > $ROOT/autogen.xml

find . -name *.png >> $ROOT/autogen.xml -exec bash -c 'add_file "$0"' {} \;

echo "  </images>" >> $ROOT/autogen.xml


# TODO notify directory switches
# => new tag


echo "</resources>" >> $ROOT/autogen.xml

# end script, printing result
if [ $DEBUG = 1 ] ; then
  echo "resulting XML:" ;
  cat $ROOT/autogen.xml ;
fi
