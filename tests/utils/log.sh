#!/bin/bash


# Colors for fancy prints
COLOR_ERROR='\e[0;31m'
COLOR_SUCCESS=$(echo -e '\e[0;32m')
COLOR_NORMAL=$(echo -e '\e[0m')
COLOR_WARNING=$(echo -e '\e[0;33m')


function printError()
{
  echo -e "${COLOR_ERROR}$1${COLOR_NORMAL}" 1>&2
}
