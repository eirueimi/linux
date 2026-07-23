#!/usr/bin/env bash
# 26-01-capable チェッカー: 期待マーカーが dmesg に出るか
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
[ -f capcheck.ko ] || { echo "FAIL: capcheck.ko が生成されていません"; exit 1; }
$SUDO rmmod capcheck 2>/dev/null || true
$SUDO insmod capcheck.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
hit=$($SUDO dmesg | tail -n 30 | grep -cE "m26sec: uid=[0-9]+ CAP_SYS_ADMIN=[01]")
$SUDO rmmod capcheck 2>/dev/null || true
if [ "$hit" -ge 1 ]; then echo "PASS"; exit 0
else echo "FAIL: 期待するマーカーが見つかりません"; exit 1; fi
