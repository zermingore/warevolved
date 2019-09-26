#!/bin/bash


# Colors for fancy prints
COLOR_ERROR='\e[0;31m'
COLOR_SUCCESS=$(echo -e '\e[0;32m')
COLOR_NORMAL=$(echo -e '\e[0m')
COLOR_WARNING=$(echo -e '\e[0;33m')
COLOR_INFO=$(echo -e '\e[0;34m')


function printError()
{
  echo -e "${COLOR_ERROR}$1${COLOR_NORMAL}" 1>&2
}

function printSuccess()
{
  echo -e "${COLOR_SUCCESS}$1${COLOR_NORMAL}"
}

function printInfo()
{
  echo -e "${COLOR_INFO}$1${COLOR_NORMAL}"
}



function beginSection()
{
  echo "${COLOR_INFO}" # Set the color for the full function

  # Center text + draw horizontal line under it
  local col="${COLUMNS:-$(tput cols)}"
  printf "%*s\n" $(((${#1} + col) / 2)) "$1"
  printf '%*s\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' _

  echo "${COLOR_NORMAL}" # Reset color
}

function endSection()
{
  # Draw a horizontal line
  printf '%*s\n\n\n' "${COLUMNS:-$(tput cols)}" '' | tr ' ' _
}
