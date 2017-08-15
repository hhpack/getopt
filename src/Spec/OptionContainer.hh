<?hh //strict

/**
 * This file is part of hhpack\getopt package.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace HHPack\Getopt\Spec;


interface OptionContainer
{
    /**
     * Check if it has an argumentless option.
     */
    public function hasNoValue(string $name) : bool;

    /**
     * Check if it has an option to take one argument.
     */
    public function hasOneValue(string $name) : bool;
}
