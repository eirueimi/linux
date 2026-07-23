#!/usr/bin/env bash
# 05 モジュールパラメータ チェッカー
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
$SUDO rmmod hello 2>/dev/null || true
$SUDO insmod hello.ko name=__CHECK__ 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
hit=$($SUDO dmesg | tail -n 20 | grep -c "hello: hello, __CHECK__")
$SUDO rmmod hello 2>/dev/null
if [ "$hit" -ge 1 ]; then echo "PASS"; exit 0
else echo "FAIL: パラメータ name=__CHECK__ が反映されていません"; exit 1; fi
