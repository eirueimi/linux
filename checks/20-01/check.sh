#!/usr/bin/env bash
# 20-01-exec-trace チェッカー: パッチ適用後の6.6をビルドしQEMU起動、busybox initramfsで
# 目的のカーネルパス（mount/exec）を通し、ブートログにマーカーが出るか検査する。
set -u
command -v make >/dev/null || { echo "SKIP: make が見つかりません"; exit 2; }
command -v qemu-system-x86_64 >/dev/null || { echo "SKIP: qemu-system-x86_64 が見つかりません"; exit 2; }
BB=$(command -v busybox) || true
[ -n "${BB:-}" ] || { echo "SKIP: busybox（静的推奨）が必要です"; exit 2; }
make -j"$(nproc)" bzImage >/dev/null 2>&1 || { echo "FAIL: ビルドに失敗しました"; exit 1; }
root=$(mktemp -d); mkdir -p "$root/bin" "$root/proc" "$root/sys"
cp "$BB" "$root/bin/busybox"
( cd "$root/bin" && for a in sh mount dmesg grep poweroff cat; do ln -sf busybox "$a"; done )
{
  printf '#!/bin/sh\n'
  printf 'export PATH=/bin\n'
  printf 'mount -t proc proc /proc\n'
  printf 'dmesg | grep -F "%s"\n' "m20exec:"
  printf 'echo ===END===\n'
  printf 'poweroff -f\n'
} > "$root/init"; chmod +x "$root/init"
ir=$(mktemp); ( cd "$root" && find . | cpio -o -H newc 2>/dev/null | gzip ) > "$ir"
log=$(mktemp)
timeout 120 qemu-system-x86_64 -kernel arch/x86/boot/bzImage -initrd "$ir"   -append "console=ttyS0 panic=1 loglevel=7" -nographic -no-reboot -serial "file:$log" </dev/null >/dev/null 2>&1 || true
rm -rf "$root" "$ir"
if grep -Fq "m20exec:" "$log"; then echo PASS; rm -f "$log"; exit 0
else echo "FAIL: ブートログにマーカー(m20exec:)が見つかりません"; rm -f "$log"; exit 1; fi
