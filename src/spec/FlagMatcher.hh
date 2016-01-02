<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace hhpack\getopt\spec;

final class FlagMatcher implements Matcher
{

    public function __construct(
        private string $name
    )
    {
    }

    public function name() : string
    {
        return $this->name;
    }

    public function matches(string $name) : bool
    {
        $pattern = '/^(' . $this->name() . ')$/';
        return preg_match($pattern, $name) === 1;
    }

}
