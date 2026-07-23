#!/usr/bin/env bash
# 06-01-spinlock チェッカー: 期待マーカーが dmesg に出るか
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
[ -f spinlock.ko ] || { echo "FAIL: spinlock.ko が生成されていません"; exit 1; }
$SUDO rmmod spinlock 2>/dev/null || true
$SUDO insmod spinlock.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
hit=$($SUDO dmesg | tail -n 30 | grep -cE "m6sync: counter=1000")
$SUDO rmmod spinlock 2>/dev/null || true
if [ "$hit" -ge 1 ]; then echo "PASS"; exit 0
else echo "FAIL: 期待するマーカーが見つかりません"; exit 1; fi
