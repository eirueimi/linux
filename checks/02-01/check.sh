#!/usr/bin/env bash
# 02-01 current チェッカー: insmod したプロセス(insmod)の comm/pid が出るか
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
[ -f current.ko ] || { echo "FAIL: current.ko が生成されていません"; exit 1; }
$SUDO rmmod current 2>/dev/null || true
$SUDO insmod current.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
# insmod で読み込むので comm は "insmod"、pid は数値
hit=$($SUDO dmesg | tail -n 20 | grep -cE "m2cur: current: insmod \(pid [0-9]+\)")
$SUDO rmmod current 2>/dev/null || true
if [ "$hit" -ge 1 ]; then echo "PASS"; exit 0
else echo "FAIL: current->comm/pid の出力が見つかりません（insmod のプロセスとして出るはず）"; exit 1; fi
