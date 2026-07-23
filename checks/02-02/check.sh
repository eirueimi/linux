#!/usr/bin/env bash
# 02-02 walk チェッカー: プロセス数が妥当な下限以上か
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
$SUDO rmmod walk 2>/dev/null || true
$SUDO insmod walk.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
line=$($SUDO dmesg | tail -n 20 | grep -oE "m2walk: process count = [0-9]+" | tail -n1)
$SUDO rmmod walk 2>/dev/null || true
n=$(printf '%s' "$line" | grep -oE "[0-9]+$")
if [ -n "$n" ] && [ "$n" -ge 5 ]; then echo "PASS ($line)"; exit 0
else echo "FAIL: プロセス数の出力が無い/少なすぎます（どんなLinuxでも5以上あるはず）"; exit 1; fi
