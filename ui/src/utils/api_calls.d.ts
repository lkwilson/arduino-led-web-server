interface RandomModeConfig {
  type: "IDLE"|"UNIFORM";
  delay_duration?: number;
  fade_duration?: number;
}

interface IdleConfig {

}

type ModeConfig = RandomModeConfig | IdleConfig;

interface LedDataEntry {
  index: number;
  red?: number;
  green?: number;
  blue?: number;
  delay_duration?: number;
  fade_duration?: number;
}

interface LedsData {
  red: number;
  green: number;
  blue: number;
  delay_duration?: number;
  fade_duration?: number;
}
