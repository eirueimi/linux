#!/usr/bin/env bash
# 08-01-virt-phys チェッカー: 期待マーカーが dmesg に出るか
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
[ -f virtphys.ko ] || { echo "FAIL: virtphys.ko が生成されていません"; exit 1; }
$SUDO rmmod virtphys 2>/dev/null || true
$SUDO insmod virtphys.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
hit=$($SUDO dmesg | tail -n 30 | grep -cE "m8addr: va=0x[0-9a-f]+ pa=0x[0-9a-f]+")
$SUDO rmmod virtphys 2>/dev/null || true
if [ "$hit" -ge 1 ]; then echo "PASS"; exit 0
else echo "FAIL: 期待するマーカーが見つかりません"; exit 1; fi
