#!/usr/bin/env bash
# 09-02 kmalloc/vmalloc チェッカー: m9alloc モジュールが kmalloc/vmalloc 両方のアドレスを出すか
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
[ -f m9alloc.ko ] || { echo "FAIL: m9alloc.ko が生成されていません"; exit 1; }
$SUDO rmmod m9alloc 2>/dev/null || true
$SUDO insmod m9alloc.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
hit=$($SUDO dmesg | tail -n 20 | grep -cE "m9alloc: kmalloc=.*vmalloc=")
$SUDO rmmod m9alloc 2>/dev/null || true
if [ "$hit" -ge 1 ]; then echo "PASS"; exit 0
else echo "FAIL: kmalloc/vmalloc のアドレス出力が見つかりません（両方確保できているか確認）"; exit 1; fi
