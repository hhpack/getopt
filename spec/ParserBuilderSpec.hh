<?hh //partial

namespace hhpack\getopt\spec;

use hhpack\getopt\OptionParserBuilder;
use hhpack\getopt\NamedMatcher;
use hhpack\getopt\OptionValue;
use hhpack\getopt\StringConsumeHandler;
use hhpack\getopt\BoolConsumeHandler;
use hhpack\getopt\ValueType;

describe(OptionParserBuilder::class, function () {
  describe('addOption', function () {
    beforeEach(function () {
      $this->builder = new OptionParserBuilder();
      $this->builder->addOption(
        new OptionValue(
          new BoolConsumeHandler('debug', [ '-d', '--debug' ]),
          false,
          ValueType::Optional
        )
      );
    });
    it('should option added', function () {
      $optionCount = $this->builder->optionCount();
      expect($optionCount)->toBe(1);
    });
  });
});
