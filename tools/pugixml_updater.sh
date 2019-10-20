#/bin/sh

# Check if there is a new pugixml release
# This script must be called from the root folder
# It was written to avoid have the full pugixml as submodule / subtree

# Warning:
# - License changes are not tracked
# - The sources are assumed to be in src/
# - New version can be unseen if they are not of the form 'v\d(.\d*)*
# - The script will not commit anything but modifies tracked files



set -e

PUGIXML_URL=https://github.com/zeux/pugixml.git
PUGIXML_VERSION_PATTERN='v[0-9]+(\.[0-9]*)*'


# Get the current used release
LOCAL_VERSION=$(grep ' pugixml (v' README | egrep -o $PUGIXML_VERSION_PATTERN)

# Get the last remote version
ONLINE_VERSION=$(git ls-remote --tags "$PUGIXML_URL" \
  | egrep -o $PUGIXML_VERSION_PATTERN \
  | sort -V \
  | tail -n 1)

# Stop here if the version is already the same
if [ $LOCAL_VERSION == $ONLINE_VERSION ]; then
  echo "Already using the last version $ONLINE_VERSION"
  exit 0
fi


echo "Updating: $LOCAL_VERSION -> $ONLINE_VERSION"

# Checkout the current version to update the local one
PUGIXML_TMP=/tmp/pugi_$(date +%s)
git clone -q --branch "$ONLINE_VERSION" --depth 1 "$PUGIXML_URL" $PUGIXML_TMP
cp ${PUGIXML_TMP}/src/* lib/pugixml/
cp ${PUGIXML_TMP}/readme.txt lib/pugixml/
cp ${PUGIXML_TMP}/LICENSE.md lib/pugixml/

# Update the version in the README
sed -i s/" pugixml ($LOCAL_VERSION)"/" pugixml ($ONLINE_VERSION)"/ README
