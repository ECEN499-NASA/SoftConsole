#!/bin/sh
cd D:/Project-499/SoftConsole
git add --all
timestamp() {
  date +"at  %H:%M on %m/%d/%Y"
}
git commit -am "auto-commit : Update by Kyle $(timestamp)"
git pull
git push origin master