<?hh //partial

namespace hhpack\getopt\spec\parser;

use hhpack\getopt\parser\ParsedResult;

describe(ParsedResult::class, function () {
  describe('map', function () {
    beforeEach(function () {
      $this->result = new ParsedResult(
        [ 'foo' ],
        [ Pair { 'name', string } ]
      );
    });
    it('return the result of applying the mapper', function () {
      $argCount = $this->result->map(($result) ==> $result->argumentCount());
      expect($argCount)->toBe(1);
    });
  });
});
