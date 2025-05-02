<?php

/**
 * @generate-function-entries
 * @generate-class-entries
 */

function mygmp_version(): void {}

function mygmp_get_version(): string {}

function mygmp_add(string $a, string $b): string|null {}
function mygmp_add_array(array $arr): string|null {}

function mygmp_sum(array $nums): string|null {}

function mygmp_random_ints(int $count, int $bits = 64): array|null {}

class MyGMP {
    public function __construct(int|float|string $num = 0) {}
    public function __toString(): string {}
    public function __debugInfo(): array {}

    public function add(\MyGMP|int|float|string $other): \MyGMP {}
    public function sub(\MyGMP|int|float|string $other): \MyGMP {}
    public function mul(\MyGMP|int|float|string $other): \MyGMP {}
    public function divq(\MyGMP|int|float|string $other): \MyGMP {}
}
