#!/usr/bin/env bash
# 09-04 自作slabキャッシュ チェッカー: m9slab モジュールがキャッシュ作成・確保に成功するか
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
[ -f m9slab.ko ] || { echo "FAIL: m9slab.ko が生成されていません"; exit 1; }
$SUDO rmmod m9slab 2>/dev/null || true
$SUDO insmod m9slab.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
hit=$($SUDO dmesg | tail -n 20 | grep -cE "m9slab: created and allocated")
$SUDO rmmod m9slab 2>/dev/null || true
if [ "$hit" -ge 1 ]; then echo "PASS"; exit 0
else echo "FAIL: m9slab のキャッシュ作成・確保の出力が見つかりません"; exit 1; fi
