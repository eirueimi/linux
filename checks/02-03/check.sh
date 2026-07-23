#!/usr/bin/env bash
# 02-03 parent チェッカー: 親を辿って pid 1 に到達したか
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
$SUDO rmmod parent 2>/dev/null || true
$SUDO insmod parent.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
hit=$($SUDO dmesg | tail -n 40 | grep -cE "m2parent: .+ \(pid 1\)")
$SUDO rmmod parent 2>/dev/null || true
if [ "$hit" -ge 1 ]; then echo "PASS"; exit 0
else echo "FAIL: 親を辿って pid 1 のプロセスを出力できていません"; exit 1; fi
