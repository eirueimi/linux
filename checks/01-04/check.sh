#!/usr/bin/env bash
# 04 Hello モジュール チェッカー
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
if [ "$(id -u)" -ne 0 ] && ! command -v sudo >/dev/null; then echo "SKIP: root権限が必要です"; exit 2; fi
if [ "$(id -u)" -eq 0 ]; then SUDO=""; else SUDO="sudo"; fi
make >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
[ -f hello.ko ] || { echo "FAIL: hello.ko が生成されていません"; exit 1; }
$SUDO rmmod hello 2>/dev/null || true
$SUDO insmod hello.ko 2>/dev/null || { echo "FAIL: insmod に失敗しました"; exit 1; }
ok_load=$($SUDO dmesg | tail -n 20 | grep -c "hello: loaded")
$SUDO rmmod hello 2>/dev/null
ok_unload=$($SUDO dmesg | tail -n 5 | grep -c "hello: unloaded")
if [ "$ok_load" -ge 1 ] && [ "$ok_unload" -ge 1 ]; then
  echo "PASS"; exit 0
else
  echo "FAIL: dmesg に 'hello: loaded' / 'hello: unloaded' が見つかりません"; exit 1
fi
