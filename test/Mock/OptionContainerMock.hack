namespace HHPack\Getopt\Test\Mock;

use HHPack\Getopt\Spec\OptionContainer;

final class OptionContainerMock implements OptionContainer {
  private ImmSet<string> $noArgs;
  private ImmSet<string> $oneArgs;

  public function __construct(
    Traversable<string> $noArgs,
    Traversable<string> $oneArgs,
  ) {
    $this->noArgs = ImmSet::fromItems($noArgs);
    $this->oneArgs = ImmSet::fromItems($oneArgs);
  }

  public function hasNoValue(string $name): bool {
    return $this->noArgs->contains($name);
  }

  public function hasOneValue(string $name): bool {
    return $this->oneArgs->contains($name);
  }
}
