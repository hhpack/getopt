<?hh //partial

namespace HHPack\Getopt\Spec\Parser;

use HHPack\Getopt\Parser\OptionParser;
use HHPack\Getopt\Spec\ValueType;
use HHPack\Getopt\Spec\NamedMatcher;
use HHPack\Getopt\Spec\OptionValue;
use HHPack\Getopt\Spec\RequiredException;
use HHPack\Getopt\Handler\StringConsumeHandler;

describe(OptionParser::class, function () {
  describe('parse', function () {
    context('when -- not included', function () {
      beforeEach(function () {
        $this->args = [ '-nfoo' ];
        $this->parser = OptionParser::fromOptions([
          new OptionValue(
            new StringConsumeHandler('name', [ '-n', '--name' ]),
            'foo',
            ValueType::Optional
          )
        ]);
      });
      it('return parsed result', function () {
        $result = $this->parser->parse($this->args);

        expect($result->argumentCount())->toBe(0);
        expect($result->optionCount())->toBe(1);
        expect($result->getOption('name'))->toBe('foo');
      });
    });
    context('when -- included', function () {
      beforeEach(function () {
        $this->args = [ '-nfoo', '--', 'value' ];
        $this->parser = OptionParser::fromOptions([
          new OptionValue(
            new StringConsumeHandler('name', [ '-n', '--name' ]),
            'foo',
            ValueType::Optional
          )
        ]);
      });
      it('return parsed result', function () {
        $result = $this->parser->parse($this->args);

        expect($result->argumentCount())->toBe(1);
        expect($result->optionCount())->toBe(1);
        expect($result->getOption('name'))->toBe('foo');
      });
    });
    context('when reqired option is empty', function () {
      beforeEach(function () {
        $this->parser = OptionParser::fromOptions([
          new OptionValue(
            new StringConsumeHandler('name', [ '-n', '--name' ]),
            'foo',
            ValueType::Required
          )
        ]);
      });
      it('throw required exception', function () {
        expect(function () {
          $this->parser->parse([ 'foo' ]);
        })->toThrow(RequiredException::class);
      });
    });
  });
});
