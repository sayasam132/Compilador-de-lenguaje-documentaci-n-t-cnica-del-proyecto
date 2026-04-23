#!/bin/bash
PASS=0
FAIL=0

for f in test/*.español; do
    name=$(basename "$f" .español)
    actual=$(./compiler "$f" 2>/dev/null)
    expected=$(awk "/^=== $name ===/{found=1; next} found && /^===/{ exit } found{ print }" test/EXPECTED_OUTPUTS.txt)
    if [ "$actual" = "$expected" ]; then
        echo "PASS: $name"
        PASS=$((PASS + 1))
    else
        echo "FAIL: $name"
        FAIL=$((FAIL + 1))
    fi
done

echo ""
echo "Resultados: $PASS pasaron, $FAIL fallaron"
