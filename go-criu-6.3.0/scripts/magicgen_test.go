package main

import (
	"bytes"
	"fmt"
	"reflect"
	"strings"
	"testing"
)

type testRead struct {
	in       string
	expected map[string]uint64
}

type testWrite struct {
	in       map[string]uint64
	expected string
}

func TestReadMagics(t *testing.T) {
	tests := []testRead{
		{
			// Simple
			in: "#define TEST 0xbc614e",
			expected: map[string]uint64{
				"TEST": 12345678,
			},
		},
		{
			// With duplicate
			in: `#define TEST 0xbc614e
#define V1 1
#define TEST_COPY TEST
#define RAW 0x0
`,
			expected: map[string]uint64{
				"V1":   1,
				"TEST": 12345678,
				"RAW":  0,
			},
		},
	}

	for _, test := range tests {
		got := readMagics(strings.NewReader(test.in))
		if !reflect.DeepEqual(got, test.expected) {
			t.Errorf("Got: %v\nExpected: %v", got, test.expected)
		}
	}
}

func TestWriteMagics(t *testing.T) {
	expectedPrefix := `// Code generated by magicgen. DO NOT EDIT.

package magic

type MagicMap struct {
	ByName  map[string]uint64
	ByValue map[uint64]string
}

func LoadMagic() MagicMap {
	magicMap := MagicMap{
		ByName:  make(map[string]uint64),
		ByValue: make(map[uint64]string),
	}`
	expectedSuffix := "\n\treturn magicMap\n}\n"

	tests := []testWrite{
		{
			// Simple
			in: map[string]uint64{
				"TEST": 12345678,
			},
			expected: `
	magicMap.ByName["TEST"] = 12345678
	magicMap.ByValue[12345678] = "TEST"`,
		},
		{
			// With suffix
			in: map[string]uint64{
				"TEST_MAGIC": 12345678,
			},
			expected: `
	magicMap.ByName["TEST"] = 12345678
	magicMap.ByValue[12345678] = "TEST"`,
		},
		{
			// With values to be ignored
			in: map[string]uint64{
				"V1":   1,
				"TEST": 12345678,
				"RAW":  0,
			},
			expected: `
	magicMap.ByName["TEST"] = 12345678
	magicMap.ByValue[12345678] = "TEST"`,
		},
	}

	for _, test := range tests {
		got := &bytes.Buffer{}
		want := fmt.Sprint(expectedPrefix, test.expected, expectedSuffix)
		writeMagics(got, test.in)
		if !reflect.DeepEqual(got.String(), want) {
			t.Errorf("Got: %v\nExpected: %v", got, want)
		}
	}
}