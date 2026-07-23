#!/usr/bin/env bash
# 03 起動メッセージ チェッカー（QEMU起動→シリアル検査）
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
command -v qemu-system-x86_64 >/dev/null || { echo "SKIP: qemu-system-x86_64 が見つかりません"; exit 2; }
make -j"$(nproc)" bzImage >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
log=$(mktemp)
timeout 90 qemu-system-x86_64 -kernel arch/x86/boot/bzImage \
  -append "console=ttyS0" -nographic -serial "file:$log" >/dev/null 2>&1 || true
if grep -q "Hello" "$log"; then echo "PASS"; rm -f "$log"; exit 0
else echo "FAIL: ブートログに自作メッセージ(Hello)が見つかりません"; rm -f "$log"; exit 1; fi
