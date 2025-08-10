SELECT id, visit_date, people
FROM Stadium s1
WHERE people >= 100
  AND (
      -- This row is part of a 3+ consecutive sequence (as the first)
      (EXISTS (
          SELECT 1 FROM Stadium s2
          WHERE s2.id = s1.id + 1 AND s2.people >= 100
      ) AND EXISTS (
          SELECT 1 FROM Stadium s3
          WHERE s3.id = s1.id + 2 AND s3.people >= 100
      ))
      -- This row is part of a 3+ consecutive sequence (as the middle)
      OR (EXISTS (
          SELECT 1 FROM Stadium s2
          WHERE s2.id = s1.id - 1 AND s2.people >= 100
      ) AND EXISTS (
          SELECT 1 FROM Stadium s3
          WHERE s3.id = s1.id + 1 AND s3.people >= 100
      ))
      -- This row is part of a 3+ consecutive sequence (as the last)
      OR (EXISTS (
          SELECT 1 FROM Stadium s2
          WHERE s2.id = s1.id - 1 AND s2.people >= 100
      ) AND EXISTS (
          SELECT 1 FROM Stadium s3
          WHERE s3.id = s1.id - 2 AND s3.people >= 100
      ))
  )
ORDER BY visit_date;
